import { Link } from "react-router-dom";

export default function PlaylistCard({ playlist }) {

  return (
    <Link 
      to={`/playlist/${playlist.id}`}
      className="playlist-card"
    >
      <div className="cover-container">
        <img
          src={playlist.picture_medium}
          alt={playlist.title}
          className="cover-image"
        />
      </div>
      <div className="playlist-card-title">{playlist.title}</div>
    </Link>
  );
}
