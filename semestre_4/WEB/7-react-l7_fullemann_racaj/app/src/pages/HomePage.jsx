import useSWR from "swr";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faSpinner } from "@fortawesome/free-solid-svg-icons";
import PlaylistCard from "../components/PlaylistCard";

const fetcher = (url) =>
  fetch(`http://localhost:8080${url}`).then((res) => res.json());

export default function HomePage() {
  const { data, error } = useSWR("/popular/playlists", fetcher);

  if (error)
    return <div className="center-message">Impossible de charger les playlists</div>;

  if (!data)
    return (
      <div className="center-message">
        <FontAwesomeIcon icon={faSpinner} spin size="4x" />
      </div>
    );

  return (
    <div className="home-page">
      <h1 className="title">Playlists populaires</h1>
      <div className="playlist-grid">
        {data.map((playlist) => (
          <PlaylistCard key={playlist.id} playlist={playlist} />
        ))}
      </div>
    </div>
  );
}